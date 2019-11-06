class Queen {};

class King inherits Queen {};

class A {
    temp : King;
    x : Int <- (temp <- (new Queen)); -- You cannot assign sth superior to sth inferior
};
