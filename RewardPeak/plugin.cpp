#include "plugin.h"
#include "RewardPeak.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <RewardPeak>("Utilities")
    );
    plugin->add(summation_decl);
}
