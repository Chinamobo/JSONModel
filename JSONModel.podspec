Pod::Spec.new do |s|
  s.name     = 'JSONModel'
  s.version  = '1.0.2b'
  s.license  = { :type => 'MIT', :file => 'LICENSE_jsonmodel.txt' }
  s.homepage = 'https://github.com/Chinamobo/JSONModel'
  s.authors  = { "Marin Todorov" => "touch-code-magazine@underplot.com" }
  s.summary  = 'Minimized JSONModel Repository'
  
  s.ios.deployment_target = '5.0'
  s.osx.deployment_target = '10.7'
  s.requires_arc = true
  
  s.source   = {
   :git => "https://github.com/Chinamobo/JSONModel.git",
   :tag => s.version.to_s ,
   :submodules => true
  }
  
  s.default_subspec = 'Core'

  s.public_header_files = '*.h'
  s.subspec 'Core' do |ss|
    ss.source_files = 'JSONModel.{h,m}',
      'JSONKeyMapper.{h,m}',
      'JSONModelArray.{h,m}',
      'JSONModelClassProperty.{h,m}',
      'JSONModelError.{h,m}',
      'JSONValueTransformer.{h,m}'
  end

  s.subspec 'CoreData' do |ss|
    ss.source_files = 'JSONModel+CoreData.{h,m}'
    ss.ios.frameworks = 'CoreData'
    ss.osx.frameworks = 'CoreData'
  end
end
