# Tutorial on using XSLT parameters in RENDER_STYLESHEETs

As explained in this module's main README, if a collection object has datastream with an ID of 'RENDER_STYLESHEET', it is used for all XML objects that are members of the collection, unless a member object has its own RENDER_STYLESHEET datastream. In addition, parameters can be passed to the RENDER_STYLESHEET via URL query parameters; for example, `http://host/islandora/object/islandora:29?foo=true&bar=Mark` would make the values of `foo` and `bar` accessible in the stylesheet as follows:

```xml
  <xsl:param name="foo"></xsl:param>
  <xsl:param name="bar"></xsl:param>

  <xsl:if test="$foo='true' and $bar">
    <div>Hello <span><xsl:value-of select="$bar"/></span></div>
  </xsl:if>
```

