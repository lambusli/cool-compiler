#!/usr/bin/env bash

WD="."

LEXER="lexer"
PARSER="parser"

while getopts "L:P:w:" Option
do
    case $Option in
        L)
            LEXER=$OPTARG
            ;;
        P)
            PARSER=$OPTARG
            ;;
        w)
            WD=$OPTARG
            ;;
    esac
done

shift $((OPTIND-1))

"$LEXER" $1 | "$PARSER"