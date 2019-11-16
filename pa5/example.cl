(*
    Example cool program testing as many aspects of the code generator
    as possible.
*)

class Queen {
    step : Int;
};

class King inherits Queen {
    oath : String; 
};

class Main inherits IO {
  tl : Int;
  main(): SELF_TYPE { out_string("Example!\n") };
};
