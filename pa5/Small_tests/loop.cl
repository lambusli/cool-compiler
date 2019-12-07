class Main inherits IO {
    x : Int <- 10;
    i : Int <- 0;
    main() : Object {{
        while (i < x) loop {
            out_int(i);
            out_string("\n");
            i <- i + 1;
        } pool;
    }};
};
