import { currentUserIsAdmin } from '../lib/'

describe('getUserLocale', () => {
  it('works', () => {
    if (process.platform === 'win32') {
      const isAdmin = currentUserIsAdmin()
      expect(isAdmin).not.toBeUndefined()
      console.log(isAdmin)
      expect(typeof isAdmin).toBe('boolean')
    }
    if (process.platform === 'darwin') {
      const isAdmin = currentUserIsAdmin()
      expect(isAdmin).not.toBeUndefined()
      console.log(isAdmin)
      expect(typeof isAdmin).toBe('boolean')
    }
  })
})
