(*
    Example cool program testing as many aspects of the code generator
    as possible.
*)

class Queen {
    step : Int <- 6;
    palace : Int <- 1;
    default : Object;
    retired : Bool;

    attack() : Int {0};
    retreat() : Int {0};
    drink() : Int {0};
};

class King inherits Queen {
    oath : String;
    puppet : String <- "work your mouth like a puppet";

    screwup() : Int {0};
    retreat() : Int {1};
};

class Main inherits IO {
  tl : Int;
  main(): SELF_TYPE { out_string("Example!\n") };
};
