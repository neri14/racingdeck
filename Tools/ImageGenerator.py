import base64
import os
import datetime
import sys

if len(sys.argv) != 4:
    print("Incorrect number of args, run:")
    print("python ImageGenerator.py <imagesDirPath> <outDir> <outFileBase>")
    exit(1)

imagesDirPath = sys.argv[1]
outDir = sys.argv[2]
outFileBase = sys.argv[3]

outH = os.path.join(outDir, outFileBase + '.h')
outCpp = os.path.join(outDir, outFileBase + '.cpp')

images = []
print("Generating " + outCpp)
with open(outCpp, 'w') as output:
    output.write('/** Generated on ' + str(datetime.datetime.now()) + ' **/\n')
    output.write('\n')
    output.write('#include "' + outFileBase + '.h"\n')
    output.write('\n')
    output.write('namespace Images {\n')
    output.write('    namespace Consts {\n')
    output.write('\n')

    for filename in os.listdir(imagesDirPath):
        if filename.endswith('.png'):
            name = os.path.splitext(filename)[0]
            images.append(name)
            image = 'data:image/png;base64,' + base64.b64encode(open(os.path.join(imagesDirPath, filename), 'rb').read()).decode('utf-8')
            output.write('        const std::string ' + name + ' = ')
            output.write('"' + image + '";\n')
    
    output.write('\n')
    output.write('    } // namespace Consts\n')
    output.write('} // namespace Images\n')

print("Generating " + outH)
with open(outH, 'w') as output:
    output.write('/** Generated on ' + str(datetime.datetime.now()) + ' **/\n')
    output.write('\n')
    output.write('#pragma once\n')
    output.write('\n')
    output.write('#include <string>\n')
    output.write('\n')
    output.write('namespace Images {\n')
    output.write('    namespace Consts {\n')
    output.write('\n')

    for image in images:
        output.write('        extern const std::string ' + image + ';\n')
    
    output.write('\n')
    output.write('    } // namespace Consts\n')
    output.write('} // namespace Images\n')