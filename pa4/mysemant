#!/usr/bin/env bash

BIN_DIR="$(dirname ${BASH_SOURCE[0]})/../bin"

LEXER="${BIN_DIR}/lexer"
PARSER="${BIN_DIR}/parser"
SEMANT="./semant"

usage() {
  cat << EOF
usage: $(basename "$0") [options] -- [options to coolc] FILE [FILE...]

Run lexer and parser

Options:
  -h         Print this message
  -L [FILE]  Path to lexer, default=$LEXER
  -P [FILE]  Path to parser, default=$PARSER
  -S [FILE]  Path to semant, default=$SEMANT
EOF
}

while getopts "L:P:S:h" Option
do
    case $Option in
        L)
            LEXER=$OPTARG
            ;;
        P)
            PARSER=$OPTARG
            ;;
        S)
            SEMANT=$OPTARG
            ;;
        h)
            usage
            exit 0
            ;;
        ?)
            usage
            exit 85
            ;;
    esac
done

shift $((OPTIND-1))

"$LEXER" $* | "$PARSER" $* | "$SEMANT" $*