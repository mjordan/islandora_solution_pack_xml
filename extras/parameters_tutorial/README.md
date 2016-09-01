# Tutorial on using XSLT parameters in RENDER_STYLESHEETs

As explained in this module's main README, if a collection object has a datastream with an ID of 'RENDER_STYLESHEET', the XSLT transform in that datastream is applied to all XML objects that are members of the collection, unless a member object has its own RENDER_STYLESHEET datastream. In addition, parameters can be passed to the RENDER_STYLESHEET via URL query parameters, as long as the paramters are declared in the stylesheet; for example, `http://host/islandora/object/islandora:29?foo=true&bar=Mark` would make the values of `foo` and `bar` accessible in the stylesheet as follows:

```xml
  <xsl:param name="foo"></xsl:param>
  <xsl:param name="bar"></xsl:param>

  <xsl:if test="$foo='true' and $bar">
    <div>Hello <span><xsl:value-of select="$bar"/></span></div>
  </xsl:if>
```

This tutorial illustrates how URL parameters passed to a RENDER_STYLESHEET can be used to transform a single XML object, namely an excerpt of Cory Doctorow's Down and Out in the Magic Kingdom marked up in DocBook, in a variety of ways.

