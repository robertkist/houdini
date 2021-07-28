# Various Houdini HDAs and VEX snippets

1. Clone this repo
2. Include into your Vex path:

Mac / Linux: Edit your houdini.env file and add:

```HOUDINI_VEX_PATH = /<path>/houdini_hda/^;&```

Windows: Edit your houdini.env file and add:

```HOUDINI_VEX_PATH = D:/<path>/houdini_hda/vex/^;&```

Where houdini_hda is this repository and path the location where it resides.

3. Include in your own Vex code:

```#include "mylib.h"```
