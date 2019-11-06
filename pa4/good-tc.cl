class Queen {
    xq1 : Int <- (new SELF_TYPE);
    xq2 : Int <- (new A);
};

class King inherits Queen {
    xk1 : Int <- (new SELF_TYPE);
};

class A {
    x : Bool <- true;
};

class B {
    y : Int <- 10;
};

class C {
    z : String <- "here";
};

class D {
    temp : Int;
    x : Int <- (temp <- 5);
    tempK : King;
    tempQ : Queen;
    xp : Int <- (tempQ <- tempK); -- You cannot assign sth superior to sth inferior
    xp2 : Int <- (tempQ <- new King);
};
