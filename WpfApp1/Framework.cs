using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HostRender {
    public class Framework {
        private IntPtr _framework;

        public Framework() { _framework = RenderAPI.Create(); GetFramework = _framework; }

        public static IntPtr GetFramework { get; private set; }
    }
}
