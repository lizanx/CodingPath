package main

import (
	"encoding/base64"
	"fmt"
	"net/http"
	"time"
)

func main() {
	http.HandleFunc("/set_msg", setMsgHandler)
	http.HandleFunc("/get_msg", getMsgHandler)
	http.ListenAndServe("localhost:2999", nil)
}

func setMsgHandler(w http.ResponseWriter, r *http.Request) {
	http.SetCookie(w, &http.Cookie{
		Name:  "flash_msg",
		Value: base64.URLEncoding.EncodeToString([]byte("Hello, world!")),
	})
}

func getMsgHandler(w http.ResponseWriter, r *http.Request) {
	c, err := r.Cookie("flash_msg")
	if err != nil {
		if err == http.ErrNoCookie {
			fmt.Fprintln(w, "No message found")
		}
		return
	}

	http.SetCookie(w, &http.Cookie{
		Name:    "flash_msg",
		MaxAge:  -1,
		Expires: time.Unix(1, 0),
	})

	msg, err := base64.URLEncoding.DecodeString(c.Value)
	if err != nil {
		fmt.Fprintln(w, "Failed to decode message, err =", err)
		return
	}
	w.Write(msg)
}
