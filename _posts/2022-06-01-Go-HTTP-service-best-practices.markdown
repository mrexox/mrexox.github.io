---
layout: post
title: 'Golang HTTP service best practices'
date: 2022-06-01 20:55:48 +0300
categories: go
---
# Hi, gopher!

It is hard to write a perfect Golang service on the first try. You always face some requirements you've missed and try to make the service more convenient. So here are **my own** best practices on *"How to write a cool Go HTTP service"*. I want to document it once and never think of it anymore (because devs are *lazy* by definition).

# Project structure

Imagine we need to develop a service that will handle 1-2 HTTP requests and do some logic on them. The main idea is - not to mix *business logic* with *serving*. Serving must handle interactions with the environment, and business logic is for your business.

So, I like having this structure:

```
├── main.go
├── config
│   └── config.go
├── server
│   └── server.go
└── internal
   └── ...
```

- **main.go** - is for your app entry point. Here we do initialization, start HTTP server, read configs and apply them, and handle interrupts.
- **config** - is for config structures.
- **server** - is for the HTTP serving stuff. We might want to change the server implementation or add some cool settings or features (like proxies). I should never touch the application logic.
- **internal** - the business logic of the app.

There are approaches with **api** folder and many others, but for 1-2 HTTP requests, we don't need a considerable API, right?

The main idea is:

> Separated things are easier to maintain.

# Avoid init()

I don't like implicit things in web services. It is convenient sometimes, but it is simpler to write an extra function call inside `main()` and test it accordingly.

> `init()` can make things more difficult.

# Keep server logic separated

The server. You can easily extend it without making it hard to read and maintain. Better see an example:

**server/server.go**

```go
package server

import (
    "context"

    "github.com/mrexox/project/config"

    // ...
)

type Server struct {
    // some important stuff
}

func NewServer(cfg *config.Config) *Server {
    // initialization
    return &Server{
        // ...
    }
}

func (s *Server) Start() {
    // start the HTTP server
}

func (s *Server) Shutdown(ctx context.Context) error {
    // Gracefully shutdown with the context
}
```

**main.go**

```go
package main

import (
   "github.com/mrexox/project/config"
   "github.com/mrexox/project/server"

   // ...
)

func main() {
    cfg := config.NewConfig()
    srv := server.NewServer(cfg)
    // Add handlers...
    // Handle shutdown...
}
```

The main idea is:

> Keep the server implementation and business logic separated.

# Handle SIGINT and SIGTERM

Just handling the first Ctrl-C as **Stop gracefully, please!** and the second Ctrl-C as **Stop it right now!**.

```go
func main() {
    // This is our force shutdown context
    ctx, forceShutdown := context.WithCancel(context.Background())

    // ...

    srv.Start() // should use goroutine by the way

    signalChan := make(chan os.Signal, 1)
    signal.Notify(signalChan, syscall.SIGINT, syscall.SIGTERM)

    <-signalChan
    log.Info("shutting down...")

    // Force shutdown on second signal
    go func() {
    <-signalChan
    forceShutdown()
    }()

    // If we use forceShutdown the server must shut down imediately
    if err := srv.Shutdown(ctx); err != nil {
        log.Fatal("shutdown error")
    }

    log.Info("successful shutdown")
}
```

The main idea is:

> Make the app shutdownable. It will be useful for any infrastructure you deploy it to - especially Kubernetes.

# Write tests!

Yes, this is the most important best practice of mine! Tests allow you to make sure you are not breaking the whole system by touching one thing. They say the **coverage of 70% is enough**, but I like it to be **90%** or around.

The main idea is:

> Tests are helping you control the changes. You sleep well when you have them.

# Go is fun!

There is an example of using these best practices here: [asyncproxy](https://github.com/mrexox/asyncproxy). **Asyncproxy** is a service for balancing the load by storing request bodies in a database and proxying them asynchronously. I had much fun writing it. And this is because, you know, using Go is fun!
