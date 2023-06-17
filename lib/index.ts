type NativeModule = {
  currentUserIsAdmin: () => boolean
}

// The native binary will be loaded lazily to avoid any possible crash at start
// time, which are harder to trace.
let _nativeModule: NativeModule | undefined = undefined

function getNativeModule() {
  _nativeModule = require('bindings')('check-current-user-is-admin.node')
  return _nativeModule
}

export function currentUserIsAdmin(): boolean {
  const result = getNativeModule()?.currentUserIsAdmin()
  return !!result
}
