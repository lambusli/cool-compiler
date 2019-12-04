class Main inherits IO {
    x : Int;
    y : Int <- 5;
    flag : Bool;
    alter(s : String) : Object {{
        s <- "\nI have changed\n";
        out_string(s);
    }};
    main() : Object {{
        x <- y;
        out_int(x);
        alter("me");
        flag <- true; 
    }};
};
