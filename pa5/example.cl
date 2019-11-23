(*
    Example cool program testing as many aspects of the code generator
    as possible.
*)

class Queen {
    step : Int;
    palace : Int;
    default : Object;
    retired : Bool;

    attack() : Int {0};
    retreat() : Int {0};
    drink() : Int {0};
};

class King inherits Queen {
    oath : String;
    puppet : String;

    screwup() : Int {0}; 
    retreat() : Int {1};
};

class Main inherits IO {
  tl : Int;
  main(): SELF_TYPE { out_string("Example!\n") };
};
