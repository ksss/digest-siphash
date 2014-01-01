require 'mkmf'

$preload = %w[digest]

create_makefile('digest/siphash/siphash')
