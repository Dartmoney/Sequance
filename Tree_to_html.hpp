//
// Created by islam on 18.06.2025.
//

#ifndef LABA3_TREE_TO_HTML_HPP
#define LABA3_TREE_TO_HTML_HPP
#include <fstream>
#include <string>
#include <sstream>
#include "Tree.hpp"


template<typename T>
void exportTreeToHtml(Tree<T>* tree, const std::string& filename);

template<typename T>
void serializeNode(std::ostream& out, TreeNode<T>* node) {
    if (!node) return;

    out << "{ \"name\": \"" << node->getData() << "\"";
    if (node->leftPtr || node->rightPtr) {
        out << ", \"children\": [";
        bool first = true;
        if (node->leftPtr) {
            serializeNode(out, node->leftPtr);
            first = false;
        }
        if (node->rightPtr) {
            if (!first) out << ", ";
            serializeNode(out, node->rightPtr);
        }
        out << "]";
    }
    out << " }";
}

template<typename T>
void serializeTree(std::ostream& out, TreeNode<T>* root) {
    serializeNode(out, root);
}

template<typename T>
void exportTreeToHtml(Tree<T> tree, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    file << R"HTML(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <script src="https://d3js.org/d3.v7.min.js"></script>
  <style>
    .node circle { fill: #fff; stroke: steelblue; stroke-width: 3px; }
    .node text { font: 12px sans-serif; }
    .link { fill: none; stroke: #ccc; stroke-width: 2px; }
  </style>
</head>
<body>
<svg width="960" height="600"></svg>
<script>
const data =
)HTML";

    serializeTree(file, tree.getRoot());
    file << ";\n";

    file << R"HTML(
const svg = d3.select("svg"),
      width = +svg.attr("width"),
      height = +svg.attr("height");

const g = svg.append("g").attr("transform", "translate(40,0)");

const treeLayout = d3.tree().size([height, width - 160]);
const root = d3.hierarchy(data);
treeLayout(root);

g.selectAll(".link")
  .data(root.links())
  .join("path")
    .attr("class", "link")
    .attr("d", d3.linkHorizontal()
        .x(d => d.y)
        .y(d => d.x));

const node = g.selectAll(".node")
  .data(root.descendants())
  .join("g")
    .attr("class", "node")
    .attr("transform", d => `translate(${d.y},${d.x})`);

node.append("circle").attr("r", 10);
node.append("text")
    .attr("dy", 3)
    .attr("x", d => d.children ? -12 : 12)
    .style("text-anchor", d => d.children ? "end" : "start")
    .text(d => d.data.name);
</script>
</body>
</html>
)HTML";

    file.close();
}

#endif //LABA3_TREE_TO_HTML_HPP
