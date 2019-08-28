#!/usr/bin/env bash

set -e

WD="."

LEXER="lexer"
PARSER="parser"
SEMANT="semant"
CGEN="cg"
SPIM="spim"
TRAP_HANDLER="trap.handler"

while getopts "L:P:S:C:M:H:w:" Option
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
        C)
            CGEN=$OPTARG
            ;;
        M)
            SPIM=$OPTARG
            ;;
        H)
            TRAP_HANDLER=$OPTARG
            ;;
        w)
            WD=$OPTARG
            ;;

    esac
done

shift $((OPTIND-1))

SFILE="${WD}/$(basename "$1").s"
"$LEXER" "$1" | "$PARSER" | "$SEMANT" | "$CGEN" -o "$SFILE"
"$SPIM" -exception_file "$TRAP_HANDLER" -f "$SFILE" | \
    grep -v "^All Rights Reserved." | \
    grep -v "^Loaded: "
