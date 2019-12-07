class Main inherits IO {
    s : String <- "I am arg\n";
    run(y : Int) : Object {{
        let s : String <- "\nI am let init\n", x : Int <- 5 in {
            out_int(x + y);
            out_string(s);
        };
        let s : String <- "outrun\n" in out_string(s);
    }};

    main() : Object {{
        let s : String, x : Int in {
            out_int(x);
            out_string(s); 
        };
    }};
};
