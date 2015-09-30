(defproject echo-server "0.1.0-SNAPSHOT"
  :description "FIXME: write description"
  :url "http://example.com/FIXME"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :repl-options {:nrepl-middleware [clojure.core.typed.repl/wrap-clj-repl]}
  :dependencies [[org.clojure/clojure "1.7.0"]
                 [org.clojure/core.typed "0.3.12-SNAPSHOT"
                  :exclusions [org.clojure/tools.nrepl]]
                 [org.clojure/tools.nrepl "0.2.11"]])
