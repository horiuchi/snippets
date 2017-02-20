class DivRect

  def divide_( input )
    return [[], 0] if input.size == 0
    result = Array.new( input.size ).map!{ Array.new( input[0].size, 0 ) }
    lastArea = 0
    rectRanges = {}
    input.each_with_index do | row, y |
      start = -1
      row.each_with_index do | e, x |
        if e == 1
          area = _check_input(result, x, y, -1, 0)
          if area <= 0
            lastArea += 1
            area = lastArea
          end
          result[y][x] = area
          if start < 0
            start = x
          end
        elsif start >= 0

        end
      end
      
      
    end
  end

  def _check_input( result, x, y, dx, dy )
    if dx != 0
      return _check_input_x(result, x, y, dx)
    elsif dy != 0
      return _check_input_y(result, x, y, dy)
    else
      return result[y][x]
    end
  end

  def _check_input_x( result, x, y, d )
    if d == -1 && x == 0
      return -1
    end
    if d == 1 && x == input[0].size - 1
      return -1
    end
    return result[y][x+d]
  end

  def _check_input_y( result, x, y, d )
    if d == -1 && y == 0
      return -1
    end
    if d == 1 && y == input.size - 1
      return -1
    end
    return result[y+d][x]
  end


  def divide( input )
    return [] if 0 == input.size
    result = Array.new( input.size ).map!{ Array.new( input[0].size, 0 ) }
    rectCount = 0
    rectRanges = {}
    for y in 0..input.size-1
      for x in 0..input[y].size-1
        if 0 == result[y][x] && 1 == input[y][x]
          rectCount += 1
          start = x
          len = 0
          for i in x..input[y].size-1
            break if 0 == input[y][i]
            result[y][i] = rectCount
            len += 1
          end
          for j in y+1..input.size-1
            break if ( 0 < start && 0 != input[j][start-1] ) ||
                     ( start+len < input[j].size && 0 != input[j][start+len] )
            matchLine = true
            for k in start..start+len-1
              if 0 == input[j][k]
                matchLine = false
                break
              end
            end
            if matchLine
              for k in start..start+len-1
                result[j][k] = rectCount
              end
            else
              break
            end
          end
        end
      end
    end
    return result
  end

end
