# Documentation

## API

```typescript
import { currentUserIsAdmin } from 'check-current-user-is-admin'

const result = currentUserIsAdmin()
console.log(result)
```

## Setup

```shellsession
$ git clone https://github.com/beyondkmp/check-current-user-is-admin.git
$ cd check-current-user-is-admin
$ yarn
```

As this project builds a native module, you'll need these dependencies along
with a recent version of Node:

- [Python](https://www.python.org/downloads/windows/)
  - _Let Python install for all users and (customized install) and \_ensure the
    **Add python.exe to Path** option is selected._
- One of Visual Studio 2019, Visual C++ Build Tools or Visual Studio 2019
  - [Visual C++ Build Tools](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools)
    - _Run `npm config set msvs_version 2019` to tell node to use this
      toolchain._
  - [Visual Studio 2019](https://www.visualstudio.com/vs/community/)
    - _Ensure you select the **Desktop development with C++** feature as that is
      required by Node.js for installing native modules._
    - _Run `npm config set msvs_version 2019` to tell node to use this
      toolchain._
- Xcode
