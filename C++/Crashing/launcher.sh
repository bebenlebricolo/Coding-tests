#!/bin/bash

echo "Launching crashing program ... "
command='./crashing'
$command | tee /tmp/toto.txt
pipecode=${PIPESTATUS[0]}
errorcode=$?
echo "Error code = $errorcode"
echo "Pipe status 0 = ${pipecode}"
