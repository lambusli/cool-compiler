#!/usr/bin/env bash

WD="."

LEXER="lexer"

while getopts "L:w:" Option
do
    case $Option in
        L)
            LEXER=$OPTARG
            ;;
        w)
            WD=$OPTARG
            ;;
    esac
done

shift $((OPTIND-1))

"$LEXER" $1