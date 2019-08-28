#!/usr/bin/env bash

set -e

WD="."

COOL="coolc"
SPIM="spim"
TRAP_HANDLER="trap.handler"

while getopts "C:M:H:w:" Option
do
    case $Option in
        C)
            COOL=$OPTARG
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
"$COOL" -o "$SFILE" $*
"$SPIM" -exception_file "$TRAP_HANDLER" -f "$SFILE" | \
    grep -v "^All Rights Reserved." | \
    grep -v "^Loaded: " | \
    grep -v "GenGC initialized in test mode." | \
    grep -v "Garbage collecting ..."