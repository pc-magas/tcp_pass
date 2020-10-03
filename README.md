Reverse TCP Proxy
=================

A simple tcp recerse proxy that transfers basic TCP traffic into 3rd party servers.


What it does in a nutshell:

```
|########|
  TRAFIC          |##############|       |###############|
   FOR     >>>    | LOCAL SERVER |  ===> | REMOTE SERVER |
  REMOTE          | #############|       |###############|
  SERVER
|########|         
```

As you can se it just pipes tcp traffic from incoming connections into remote servers.


Under HEAVY DEVELOPMENT NOT READY 4 PRODUCTION