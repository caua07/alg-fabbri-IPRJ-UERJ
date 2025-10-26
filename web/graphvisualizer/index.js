class GraphVisualizer {
    constructor() {
        this.graphData = null;
        this.graphviz = null;
        this.initializeGraphviz();
        this.setupEventListeners();
    }

    async initializeGraphviz() {
        try {
            this.graphviz = await window["@hpcc-js/wasm"].Graphviz.load();
            console.log("Graphviz loaded successfully");
        } catch (error) {
            this.showMessage("Error loading Graphviz: " + error.message, "error");
        }
    }

    setupEventListeners() {
        document.getElementById('loadGraph').addEventListener('click', () => this.loadGraphData());
        document.getElementById('refreshGraph').addEventListener('click', () => this.renderGraph());
        document.getElementById('exportSvg').addEventListener('click', () => this.exportSvg());
    }

    async loadGraphData() {
        try {
            const response = await fetch('../../dataStructures/graph_data.json');
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
            this.graphData = await response.json();
            this.showMessage(`Graph loaded successfully! Nodes: ${this.graphData.nodes.length}, Edges: ${this.graphData.edges.length}`, "success");
            this.updateInfoPanel();
            this.renderGraph();
            
            // Enable buttons
            document.getElementById('refreshGraph').disabled = false;
            document.getElementById('exportSvg').disabled = false;
            
        } catch (error) {
            this.showMessage("Error loading graph data: " + error.message, "error");
            console.error("Load error:", error);
        }
    }

    updateInfoPanel() {
        if (!this.graphData) return;
        
        const info = document.getElementById('info');
        const timestamp = new Date(this.graphData.metadata.timestamp * 1000).toLocaleString();
        
        info.innerHTML = `
            <strong>Graph Information:</strong><br>
            Nodes: ${this.graphData.metadata.nodeCount} | 
            Edges: ${this.graphData.metadata.edgeCount} | 
            Last Updated: ${timestamp}
        `;
    }

    generateDotNotation() {
        if (!this.graphData) return "";

        let dot = "graph G {\n";
        dot += "  rankdir=LR;\n";
        dot += "  node [shape=circle, style=filled, fillcolor=lightblue, fontname=Arial];\n";
        dot += "  edge [fontname=Arial, fontsize=10];\n\n";

        // Add nodes
        this.graphData.nodes.forEach(node => {
            dot += `  "${node.id}" [label="${node.label}"];\n`;
        });

        dot += "\n";

        // Add edges
        this.graphData.edges.forEach(edge => {
            dot += `  "${edge.from}" -- "${edge.to}" [label="${edge.weight}", weight=${edge.weight}];\n`;
        });

        dot += "}";
        return dot;
    }

    async renderGraph() {
        if (!this.graphviz || !this.graphData) {
            this.showMessage("Graphviz not loaded or no graph data available", "error");
            return;
        }

        try {
            const dotNotation = this.generateDotNotation();
            console.log("DOT notation:", dotNotation);
            
            const svg = this.graphviz.dot(dotNotation);
            document.getElementById('graph').innerHTML = svg;
            
            this.showMessage("Graph rendered successfully!", "success");
        } catch (error) {
            this.showMessage("Error rendering graph: " + error.message, "error");
            console.error("Render error:", error);
        }
    }

    exportSvg() {
        const svgElement = document.querySelector('#graph svg');
        if (!svgElement) {
            this.showMessage("No graph to export", "error");
            return;
        }

        const svgData = new XMLSerializer().serializeToString(svgElement);
        const blob = new Blob([svgData], { type: 'image/svg+xml' });
        const url = URL.createObjectURL(blob);
        
        const a = document.createElement('a');
        a.href = url;
        a.download = 'graph.svg';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
        
        this.showMessage("Graph exported as SVG", "success");
    }

    showMessage(message, type = "info") {
        const messagesDiv = document.getElementById('messages');
        const messageDiv = document.createElement('div');
        messageDiv.className = type;
        messageDiv.textContent = message;
        
        messagesDiv.appendChild(messageDiv);
        
        // Remove message after 5 seconds
        setTimeout(() => {
            if (messageDiv.parentNode) {
                messageDiv.parentNode.removeChild(messageDiv);
            }
        }, 5000);
    }
}

// Initialize the visualizer when the page loads
document.addEventListener('DOMContentLoaded', () => {
    new GraphVisualizer();
});
