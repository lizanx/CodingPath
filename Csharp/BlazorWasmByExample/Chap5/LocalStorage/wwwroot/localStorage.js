var storage = {};

storage.setData = function (key, value) {
    localStorage.setItem(key, value);
}

storage.getData = function (key) {
    return localStorage.getItem(key);
}
