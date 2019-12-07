class Main inherits IO {
    x1 : Int <- 5;
    x2 : Int <- 5;
    x3 : Int <- 3;
    neo : IO <- new IO;
    leo : IO <- neo;
    printnum(x : Int) : Object {{
        out_int(x);
        out_string("\n");
    }};
    main() : Object {{
        printnum(5 + 3);
        printnum(5 - 3);
        printnum(5 * 3);
        printnum(5 / 3);
        if (2 <= 2) then out_string("2 <= 2\n") else out_string("not 2 <= 2\n") fi;
        if (2 < 2) then out_string("2 < 2\n") else out_string("not 2 < 2\n") fi;
        if (x1 = x2) then out_string("x1 = x2\n") else out_string("not x1 = x2\n") fi;
        if (x1 = x3) then out_string("x1 = x3\n") else out_string("not x1 = x3\n") fi;
        if ((new IO) = (new IO)) then out_string("yes object eq\n") else out_string("no object eq\n") fi;
        if (neo = leo) then out_string("neo = leo\n") else out_string("not neo = leo\n") fi; 
    }};
};
