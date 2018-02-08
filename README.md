# JSONModel

This repository provide an minimized JSONModel, which is one of the most powerful library for Cocoa development. [Some changes](#changes) may also included.

It allows you to quickly convert between json data and model with little code. JSONModel also has many advanced features, such as nested key mapping, custom value transformer, validation...

Note that the performance of JSONModel is not outstanding. It is recommended to use a background thread when handling large amounts of data.

[Checkout JSONModel Usage](https://github.com/jsonmodel/jsonmodel#basic-usage).

## Installation

Manually or using CocoaPods:

```ruby
pod 'JSONModel', :git => 'https://github.com/Chinamobo/JSONModel.git'
```

Specify a version:

```ruby
pod 'JSONModel', :git => 'https://github.com/Chinamobo/JSONModel.git', :tag => '1.7.0'
```

To use latest code:

```ruby
pod 'JSONModel', :git => 'https://github.com/Chinamobo/JSONModel.git', :branch => 'develop'
```

Carthage support comming soon.

## Changes

* Networking removed.
