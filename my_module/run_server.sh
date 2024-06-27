#!/bin/bash
# Ensure the script has executable permissions: chmod +x run_server.sh

# Start a simple HTTP server to serve the HTML and JSON files
python3 -m http.server 8000

# Open the default web browser to the URL
xdg-open http://localhost:8000/interactive_gantt.html
