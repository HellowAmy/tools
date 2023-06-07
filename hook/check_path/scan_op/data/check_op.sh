#!/bin/bash
inotifywait -mrq --timefmt '%Y-%m-%d %H:%M:%S' --format  '%T    %w    %f    %e' --event open,move,modify,delete,create /media -o check_op.log
