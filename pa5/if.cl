class Main inherits IO {
    x : Int <- 5;
    main() : Object {{
        if (true) then out_string("true\n") else out_string("false\n") fi;
        if (false) then out_string("true\n") else out_string("false\n") fi;
    }};
};
