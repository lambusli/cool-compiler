class Main inherits IO {
    x : Int <- 5;
    y : Int <- 3;
    main() : Object {{
        if (x < y) then out_string("true\n") else out_string("false\n") fi;
    }};
};
