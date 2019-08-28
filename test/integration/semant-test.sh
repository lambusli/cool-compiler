#!/usr/bin/env bash

WD="."

LEXER="lexer"
PARSER="parser"
SEMANT="semant"

while getopts "L:P:S:w:" Option
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
        w)
            WD=$OPTARG
            ;;
    esac
done

shift $((OPTIND-1))

"$LEXER" "$1" | "$PARSER" | "$SEMANT"