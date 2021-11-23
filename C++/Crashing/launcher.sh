#!/bin/bash

echo "Launching crashing program ... "
command='./crashing'
$command
errorcode=$?
echo "Error code = $errorcode"