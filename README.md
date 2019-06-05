# Hi, Admin!

There are a bunch of problems when deploying some code on multiple servers in one local network. It usually needs to be automized. While switching berween _cron_ and _ansible_ there's a solution that is aimed to do all the job. It's name is *evesync*. It is now a ruby gem that allows to synchronize files and packages (`deb` and `rpm`) between multiple nodes.

Please, keep in mind, the project is in development stage and some things are not implemented now.

## EVESYNC

It's a simple tool to automate packages and files update on different hosts, connected to one network. You need to configure it, start the daemons, and update some of the watched objects. See the [github page](https://github.com/mrexox/evesync) README file for more information and contact me if you are interested:

[mrexox@yahoo.com](mrexox@yahoo.com)


### Installing evesync

Evesync is available on [rubygems.org](https://rubygems.org/gems/evesync). Simply run:
```
# gem install evesync
```

### Running evesync

To start evesync you need to be root or make your user an owner of following directories:
- /var/run/evesync
- /var/log/evesync
- /var/lib/evesync

Non-root users will not be able to install packages. Thus running as root is recommended.

To start all daemons, go:
```
# evesync --run
```

To stop daemons, go:
```
# evesync --kill
```

### Contributing

See [README.md](https://github.com/mrexox/evesync/blob/master/README.md) for running tests and feel free to create issues and write e-mails to mrexox@yahoo.com
