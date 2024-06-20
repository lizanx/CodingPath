var jsInterop = {};

jsInterop.getWindowSize = function () {
    var size = {
        width: window.innerWidth,
        height: window.innerHeight
    }
    return size;
}

jsInterop.registerResizeHandler = function (dotnetObjRef) {
    function resizeHandler() {
        dotnetObjRef.invokeMethodAsync("GetWindowSize",
            {
                width: window.innerWidth,
                height: window.innerHeight
            }
        );
    }
    resizeHandler();
    window.addEventListener("resize", resizeHandler);
}

export { jsInterop };

export function getWindowSize() {
    return jsInterop.getWindowSize();
}
