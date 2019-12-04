class Main inherits IO {
    flag : Bool <- true;
    main() : Object {{
        while (flag) loop {
            out_string("in loop\n");
            flag <- false;
        } pool;
        out_string("out of loop\n"); 
    }};
};
