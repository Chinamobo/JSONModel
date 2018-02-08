Pod::Spec.new do |s|
  s.name         = "JSONModel"
  s.version      = "1.6.0"
  s.summary      = "Minimized JSONModel Repository."
  s.homepage     = "https://github.com/Chinamobo/JSONModel"

  s.license      = { :type => 'MIT', :file => 'LICENSE_JSONModel' }
  s.author       = { "Marin Todorov" => "touch-code-magazine@underplot.com" }

  s.source       = {
   :git => "https://github.com/Chinamobo/JSONModel.git",
   :tag => s.version.to_s
  }

  s.ios.deployment_target = '6.0'
  s.osx.deployment_target = '10.7'
  s.watchos.deployment_target = '2.0'
  s.tvos.deployment_target = '9.0'

  s.source_files = '*.{h,m}'
  s.public_header_files = '*.h'

  s.requires_arc = true

end
