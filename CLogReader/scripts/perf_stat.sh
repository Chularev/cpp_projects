#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit


sudo perf stat -d ../project/CLogReader ../data/testfile.txt "Jul 19 11:01:37*gdm-x-session[2215]*4?\""
