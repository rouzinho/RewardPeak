#include "plugin.h"
#include "RosPeak.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <RosPeak>("Utilities")
    );
    plugin->add(summation_decl);
}
