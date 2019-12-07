class Main inherits IO {
    s : Object;
    t : Object <- new String;
    x : Int <- 5;
    main() : Object {{
        --isvoid s;
        --if (isvoid s) then out_string("s is void\n") else out_string("s is not void\n") fi;
        --if (isvoid t) then out_string("t is void\n") else out_string("t is not void\n") fi;
        if (not true) then out_string("yes\n") else out_int(~x) fi;
    }};
};
