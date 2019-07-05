#include "base/Archetypes.h"

namespace gi
{
  namespace Archetypes
  {
    Entity* DefaultCamera()
    {
      Entity* camera = new Entity;

      camera->AddComponent(ComponentPtr(new C_Camera));
      camera->AddComponent(ComponentPtr(new C_Transform));
      camera->SetName("Camera");

      camera->GetComponent<C_Transform>(CT_TRANSFORM)->m_scale; // = Vec3(1600.f, 900.f);

      return camera;
    }
  }
}