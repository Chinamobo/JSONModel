Pod::Spec.new do |s|
  s.name     = 'JSONModel'
  s.version  = '1.5.1'
  s.license  = { :type => 'MIT', :file => 'LICENSE_JSONModel' }
  s.homepage = 'https://github.com/Chinamobo/JSONModel'
  s.authors  = { "Marin Todorov" => "touch-code-magazine@underplot.com" }
  s.summary  = 'Minimized JSONModel Repository'
  
  s.ios.deployment_target = '6.0'
  s.osx.deployment_target = '10.7'
  s.watchos.deployment_target = '2.0'
  s.tvos.deployment_target = '9.0'
  s.requires_arc = true
  
  s.source   = {
   :git => "https://github.com/Chinamobo/JSONModel.git",
   :tag => s.version.to_s
  }
  s.source_files = '*.{h,m}'
end
