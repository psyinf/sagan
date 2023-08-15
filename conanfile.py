from conan import ConanFile
from conan.tools.cmake import CMake

class vsg_conan_example(ConanFile):
    name = "vsg_conan_example"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = [ ("vsg/1.0.5")  
                ,("catch2/3.4.0")
                    
                #waiting for PR
                #,("vsgimgui/0.1.0")
               ]
    generators = "cmake_find_package_multi"
    
    def configure(self):
        self.options['vsg'].shared = False
        #this is currently waiting for the PR to be accepted
        #self.options['vsg'].shader_compiler = True
        
    def imports(self):    
        self.copy("*.dll", "bin", "bin")     
