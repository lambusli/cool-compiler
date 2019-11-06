class Queen {};

class King inherits Queen {};

class Bishop inherits Queen {};

class A {
    kA1 : King;
    bA1 : Bishop;
    xA1 : Int <- (if true then 5 else 3 fi);
    xA2 : Int <- (if true then "cond" else 3 fi);
    xA4 : Int <- (if true then kA1 else bA1 fi);
};
