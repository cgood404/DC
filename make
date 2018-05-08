#!/bin/bash

gcc -o dc dc.c dc_lexer.c dc_parser.c dc_builtins.c dc_memory.c -lm