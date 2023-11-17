# frozen_string_literal: true

module MkxpZ
  VERSION = "2.4.2"

  def self.get_platform_name
    if RUBY_PLATFORM =~ /cygwin|mswin|mingw|bccwin|wince|emx/
      return "win32"
    elsif RUBY_PLATFORM =~ /darwin/
      return "osx"
    else
      return "linux"
    end
  end

  def self.get_full_version_name
    base_version = MkxpZ::VERSION + "." + MkxpZ.get_platform_name
    git_hash = `git rev-parse --short HEAD`
    if git_hash != ""
      base_version += "." + git_hash
    end

    return base_version
  end
end
