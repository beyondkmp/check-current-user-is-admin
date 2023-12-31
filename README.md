# Check current user is admin

Use this package to check if current user is admin or not by native c++ code.

## Goals

- zero dependencies
- leverage TypeScript declarations wherever possible

## Install

```shellsession
$ yarn add check-current-user-is-admin
# or
$ npm install --save check-current-user-is-admin
```

## API

```typescript
import { currentUserIsAdmin } from 'check-current-user-is-admin'

const result = currentUserIsAdmin()
console.log(result)
```

## Documentation

See the documentation under the
[`docs`](https://github.com/beyondkmp/check-current-user-is-admin/tree/master/docs)
folder.

## Supported versions

Each release includes prebuilt binaries based on
[N-API](https://nodejs.org/api/n-api.html), with support for different versions
of Node and Electron. Please refer to the
[N-API version matrix](https://nodejs.org/api/n-api.html#node-api-version-matrix)
and the release documentation for [Node](https://github.com/nodejs/Release) and
[Electron](https://electronjs.org/docs/tutorial/support) to see what is
supported currently.

## Contributing

Read the
[Setup](https://github.com/beyondkmp/check-current-user-is-admin/blob/master/docs/index.md#setup)
section to ensure your development environment is setup for what you need.

If you want to see something supported, open an issue to start a discussion
about it.
