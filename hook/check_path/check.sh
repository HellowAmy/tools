#!/bin/bash
echo "== open check operation =="
sudo inotifywait -mrq --timefmt '%Y-%m-%d %H:%M:%S' --format  '%T    %w    %f    %e' --event open,move,delete,create  /media |egrep -v ".Trash-1000/*/|OPEN,ISDIR|*.swp|*.swx|*.txt~"
