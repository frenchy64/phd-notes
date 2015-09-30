;; https://gist.github.com/jvns/6910896
;; Yield a typed REPL error with cpr in vim-fireplace
(ns ^:core.typed echo-server.core
  (:require [clojure.core.typed :as t])
  (:import (java.net InetAddress DatagramPacket DatagramSocket)))

(def udp-server (t/ref :- (t/U nil DatagramSocket), nil))

(defn check-server []
  {:post [%]}
  @udp-server)

(def port 12345)

(defn ^java.net.InetAddress localhost []
  {:post [%]}
  (. InetAddress getLocalHost))

(t/ann message [String -> DatagramPacket])
(defn message [^String text]
  (new DatagramPacket (. text getBytes) (. text length) (localhost) ^int port))

(t/ann send-message [String -> t/Any])
(defn send-message [text]
  (.send (check-server) (message text)))

(defn create-udp-server []
  (DatagramSocket. port))

(defn ^:no-check start-udp-server []
  (dosync (ref-set udp-server (create-udp-server))))

(defn stop-udp-server []
  (.close @udp-server))

(defn empty-message [n] 
  (new DatagramPacket (byte-array n) n))

#_(start-udp-server)

#_(while true (do
    (def orig-packet (empty-message 1024))
    (.receive @udp-server orig-packet)
    (.send @udp-server orig-packet)
    (println ( new String (.getData orig-packet) "UTF-8"))))
